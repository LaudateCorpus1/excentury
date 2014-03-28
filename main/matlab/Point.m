classdef Point < handle
    % point object
    properties
        x
        y
    end
    methods
        function self = Point(x, y)
            self.x = x;
            self.y = y;
        end
    end
end
