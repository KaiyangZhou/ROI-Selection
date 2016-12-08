function [ pts ] = select3pts( XYZ )
% Randoly select three non-colinear points from the point list XYZ

numPts = size(XYZ,1);

found = false;
while ~found
    notstop = true;
    while notstop
        I = ceil(rand(3,1)*numPts);
        if I(1) ~= I(2) && I(1) ~= I(3) && I(2) ~= I(3)
            notstop = false;
        end
    end
    pts = XYZ(I,:);
    v1 = pts(2,:) - pts(1,:);
    v2 = pts(3,:) - pts(1,:);
    % compute value of cosine of angle between two vectors
    cosVal = dot(v1,v2) / ( norm(v1) * norm(v2) );
    
    if abs(cosVal) ~= 1
        % 3 points are not colinear
        found = true;
    end
end

end

