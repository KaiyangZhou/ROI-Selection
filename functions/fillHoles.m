function [ R ] = fillHoles( I, method, winsiRe )
% Filling holes in depth image
% input:
%   I: depth image with precision of double
%   method: 'max' or 'avg' (string)
%   winsiRe: window siRe, which is an odd number, e.g. 3, 5, 7

R = fillHoles_mex(I, method, winsiRe);

% Fill holes near the border of the image
% method: find the closest point in the known pixels and copy the value from there
R(R==0) = NaN;
[~, ind] = bwdist(~isnan(R), 'cityblock');
R(isnan(R)) = R(ind(isnan(R)));

end

