% util.SQUARE was generated on Sat Jan 04, 2014 08:39:28 PM by xcpp 
% 
%     return the square of the number.
% 
%     parameters:
% 
%       `x`: number to be squared.
%     
function varargout = square(x, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(x, 'x', {'R', '8'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = util.square_mex(len_in, in_str);
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
