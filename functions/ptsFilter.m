function [ XYZfiltered, st ] = ptsFilter( XYZ )

if isempty(XYZ)
    warning('Input is empty!');
    return;
end

xmin = min(XYZ(:,1));
xmax = max(XYZ(:,1));
zmin = min(XYZ(:,3));
zmax = max(XYZ(:,3));
rect = [xmin, xmax, zmin, zmax]; % specifying the position of grid map

% density: numCells-by-1 vector describing the density of each cell
% labels: m-by-1 vector containing a label for each datapoint
[~, labels] = ptsFilter_mex(XYZ, rect);
st = calcStdY(XYZ,labels);
indices = find(st < 0.08);
XYZfiltered = filter(XYZ,labels,indices);


% ------------------------------------------------------------
function st = calcStdY(XYZ,labels)
% ------------------------------------------------------------
numCells = 100;
st = zeros(numCells,1);

% for each cell, calculate the standard deviation along vertical axis
for i = 1:numCells
    ind = labels == i;
    if nnz(ind) ~= 0
        pts = XYZ(ind,2);
        st(i) = std(pts);
    end
end


% ------------------------------------------------------------
function XYZfiltered = filter(XYZ,labels,indices)
% ------------------------------------------------------------
num = length(indices);
XYZfiltered = [];

for i = 1:num
    cellID = indices(i);
    ind = labels == cellID;
    XYZfiltered = vertcat(XYZfiltered,XYZ(ind,:));
end


