classdef Line < handle
    % point object
    properties
        a
        b
    end
    methods
        function self = Line(x1, y1, x2, y2)
            self.a = Point(x1, y1);
            self.b = Point(x2, y2);
        end
    end
    methods(Static)
        function enable_excentury
            import excentury.dump.*
            dump_datatype('Line', 'l', { ...
                dump('l.a', 'a'), ...
                dump('l.b', 'b') ...
            });
            mload = @excentury.load.load;
            excentury.load.load_datatype('Line', { ...
                mload('$a', '{"S", "Point"}'), ...
                mload('$b', '{"S", "Point"}'), ...
                'loaded_obj = Line($a.x, $a.y, $b.x, $b.y);'
            });
        end 
    end
end
