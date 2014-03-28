% util.MAKE_LINE was generated on Sat Jan 04, 2014 08:39:28 PM by xcpp 
% 
%     Given two points, it constructs a line.
% 
%     parameters:
% 
%       `p1`: the first point.
%       `p2`: the second point.
%     
function varargout = make_line(p1, p2, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(p1, 'p1', {'S', 'Point'});
    tdump.dump(p2, 'p2', {'S', 'Point'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = util.make_line_mex(len_in, in_str);
    [val, order] = excentury.load.textparser(out_str).parse;
    if isempty(varargin)
        nout = length(order);
        varargout = cell(1, nout);
        for num=1:nout;
            varargout{num} = val(order{num});
        end
    else
        varargout{1} = val;
    end
end
