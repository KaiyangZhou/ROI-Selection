function [ bestPlane ] = ransac( XYZ, oldPlane )
% Input:
%   XYZ: point list, m-3 vectors containing 3D datapoints
%   oldPlane: plane parameters
% Output:
%   bestPlane

% Max number of iterations
% maxIter = log(1-p) / log(1-w^m)
% p: the probability that at least one of the sets of random samples does
%     not include an outlier
% w: inlier ratio
% m: minimum number of data required to determine a model
% setting: p=0.99, w=0.5, m=3
if isempty(oldPlane)
    maxIter = 35;
    bestStd = inf;
    bestSupport = 0;
else
    % less iterations because search space is refined
    maxIter = 8;
    bestPlane = oldPlane;
    [bestStd, bestSupport] = score(XYZ,bestPlane);
end

for i = 1:maxIter
    % randomly select 3 non-colinear points
    pts = select3pts(XYZ);
    % estimate new plane parameters
    theta = pts2plane(pts);
    % score new plane
    [stdVal, support] = score(XYZ, theta);
    % compare with the best one
    if support >= bestSupport && stdVal <= bestStd
        bestPlane = theta;
        bestStd = stdVal;
        bestSupport = support;
    end
end

% ------------------------------------------------------------
function [stdVal, support] = score(XYZ, plane)
% ------------------------------------------------------------
dis = calcDistance(plane, 'XYZ', XYZ);
ind = dis < 0.1;
stdVal = std(dis(ind));
support = nnz(ind);



