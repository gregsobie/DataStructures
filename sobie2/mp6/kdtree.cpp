/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	/* If values differ at specified dimension, return true if first is less, false otherwise.
	 * To break a tie, use Point's < operator */
	return (first[curDim]!=second[curDim]) ? (first[curDim] < second[curDim]) : first < second;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    	/* Distance as sum of squared differences */	
	int currentDist=0;
	for(int i=0; i<Dim; i++)	
		currentDist+=(potential[i]-target[i])*(potential[i]-target[i]);
	
	/* Distance as sum of squared differences */
	int potentialDist=0;
	for(int i=0; i<Dim; i++)
		potentialDist+=(potential[i]-target[i])*(potential[i]-target[i]);
	return (potentialDist != currentDist) ? (potentialDist<currentDist) : (potential<currentBest);
}
	
template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim>> & newPoints)
{	
    /**	
     * @todo Implement this function!	
     */
	/* Copy input list of points into a points vector */
	points=newPoints;
	/* Recursively sort vector until it represents a KDTree */	
	if(points.size()!=0)
		buildTree(0, points.size()-1, 0);
}
	
template<int Dim>	
void KDTree<Dim>::buildTree(int left, int right, int dim)
{
	/*Find the median of the vector */
	int median=(left+right)/2;
	quickSelect(left, right, dim, median);
	/* Recursive base case */
	if(left==median) return;
	if(left<median)	
		buildTree(left, median-1, (dim+1)%Dim);
	if(right>median)
		buildTree(median+1, right,(dim+1)%Dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
	Point<Dim> ret=findNNHelper(query, points[(points.size()-1)/2], 0, points.size()-1, 0);	
	return ret;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNNHelper(const Point<Dim> &query, const Point<Dim> &currentBest, int left, int right, int dim) const{	
	Point<Dim> ret=currentBest;
	int splitDim=(dim+1)%Dim;
	int oldDist=0;
	int median=(left+right)/2;
	int newMedian;
	bool searchLeft=true;

	/* If leaf node, check if closer than currentBest */	
	if (left==right){
		/* Replace if closer */	
		if (shouldReplace(query, currentBest, points[left]))	
			ret=points[left];	
		else 	ret=currentBest;
		return ret;
	}
	/* Find median of points with respect to dimension d */
	if(left<median && smallerDimVal(query, points[median], dim)){
		ret=findNNHelper(query, currentBest, left, median-1, splitDim);
		newMedian=(median+1+right-1)/2;	
		searchLeft=true;		
	}
	if(right>median && smallerDimVal(points[median], query, dim)){	
		ret=findNNHelper(query, currentBest, median+1, right, splitDim);
		newMedian=(left+median-1)/2;	
		searchLeft=false;	
	}
	/* Compare with current node, replace if closer */
	if(shouldReplace(query, ret, points[median]))
		ret=points[median];

	/* Calculate old, closest distance */
	for(int i=0; i<Dim; i++)	
		oldDist+=(query[i]-ret[i])*(query[i]-ret[i]);
	
	Point<Dim> temp=points[median];
	/* Compare old to newly calculated distance */
	if((temp[dim] - query[dim])*(temp[dim] - query[dim]) <= oldDist){
		if(left<median && !searchLeft)	
			ret=findNNHelper(query, ret, left, median-1, splitDim);	
		if(right>median && searchLeft)	
			ret=findNNHelper(query, ret, median+1, right, splitDim);		
	} 
	return ret;	
} 

/* Only recurses into one side -- the side w element we're looking for */	
template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int dim, int k)
{	
	/* Recursively subdivides into hyperrectangles */	
	while(left!=right){	
		int pivotNewIndex=partition(left, right, dim, k);	
		if(pivotNewIndex==k)	return;	
		else if(k<pivotNewIndex)	
			right=pivotNewIndex-1;
		else 	left=pivotNewIndex+1;
	}
}

/* Recursively subdivides into two convex sets -- hyperrectangles */
template<int Dim>	
int KDTree<Dim>::partition(int left, int right, int dim,  int k)	
{	
	Point<Dim> pivot=points[k];
	Point<Dim> temp=points[right];	
	points[right]=points[k];	
	points[k]=temp;
	
	int idx=left;	
	for(int i=left; i<right; i++){	
		if(smallerDimVal(points[i], pivot, dim) || points[i]==pivot){
			temp=points[idx];	
			points[idx]=points[i];	
			points[i]=temp;	
			idx++;	
		}	
	}

	temp=points[right];	
	points[right]=points[idx];	
	points[idx]=temp;	
	return idx;	
}
