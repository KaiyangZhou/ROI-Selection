function [ XYZ ] = sampling( Xw, Yw, imd, type )
% Sample datapoints for ground plane estimation

m = size(imd,1); % number of rows

switch type
    case 'all'
        X = Xw;
        Y = Yw;
        Z = imd;
    case 'upperHalf'
        s = ceil(m/2); % we sample points from the lower part of image
        X = Xw(1:s,:);
        Y = Yw(1:s,:);
        Z = imd(1:s,:);
    case 'lowerHalf'
        s = floor(m/2); % we sample points from the lower part of image
        X = Xw(s:end,:);
        Y = Yw(s:end,:);
        Z = imd(s:end,:);
end

XYZ = [X(:), Y(:), Z(:)];

% discard elements with invalid depth i.e. depth = 0
ind = XYZ(:,3) ~= 0;
XYZ = XYZ(ind,:);


end

