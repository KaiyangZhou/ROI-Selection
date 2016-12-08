function [ theta ] = pts2plane( pts )
% Calculate plane parameters using three non-colinear points
% input:
%   pts: 3-1 vectors, [x y z]
% output:
%   theta: [a b c d]', plane is defined as ax + by + cz + d = 0

D = [pts(:,1:2), ones(3,1)];
z = pts(:,3);

% Least Square
% beta = [a b d]'
beta = pinv(D) * z;

% a column vector containing plane parameters
theta = [beta(1); beta(2); -1; beta(3)];




end

