function [ dis ] = calcDistance( theta, varargin )
% Calculate distance between plane and points
% input:
%   theta: column vector containing plane parameters
%   varargin{1}: string, specifying the type of input data

eta = sqrt(sumsqr(theta(1:3)));

switch varargin{1}
    case 'XYZ'
        XYZ = varargin{2};
        % dis: a column vector containing distance information
        dis = abs(XYZ * theta(1:3) + theta(4)) / eta;
    case 'multiMaps'
        Xw = varargin{2};
        Yw = varargin{3};
        Zw = varargin{4};
        % dis: a 2D map with size equal to original depth image
        dis = abs(Xw*theta(1) + Yw*theta(2) + Zw*theta(3) + theta(4)) / eta;
end



end

