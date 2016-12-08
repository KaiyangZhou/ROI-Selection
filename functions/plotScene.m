function plotScene( imd, varargin )
% Input can be only imd or both

if nargin ~= 1
    num = numel(varargin);
    for i = 1:2:num
        name = varargin{i};
        val = varargin{i+1};
        switch name
            case 'ground'
                type = 'ground';
                theta = val;
            case 'ceiling'
                type = 'ceiling';
                theta = val;
            case 'with_roi'
                roi = val;
        end
    end
end

if ~exist('roi', 'var')
    roi = ones(size(imd));
end

imd = imd .* roi;

[Xw, Yw] = local2world(imd);
plot3(Xw,imd,Yw,'b.')
xlabel('X')
ylabel('Depth')
zlabel('Y')

if ~exist('theta', 'var')
    theta = [];
end

if ~isempty(theta)
    hold on
    m = size(imd,1);
    switch type
        case 'ground'
            newXw = Xw(round(2*m/3):end,:);
            newYw = Yw(round(2*m/3):end,:);
        case 'ceiling'
            newXw = Xw(1:round(m/3),:);
            newYw = Yw(1:round(m/3),:);
    end
    newZw = theta(1) * newXw + theta(2) * newYw + theta(4);
    % plot estimated plane
    plot3(newXw,newZw,newYw,'r.')
    hold off
end


end

