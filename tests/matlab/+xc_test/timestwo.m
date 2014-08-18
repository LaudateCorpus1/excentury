% xc_test.TIMESTWO generated on Sat Aug 16, 2014 03:45:54 PM by xcpp
% 
%     Take a scalar and double it.
% 
%     parameters:
% 
%       `x`: scalar to be doubled.
%     
function varargout = timestwo(x, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(x, 'x', {'R', '8'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = xc_test.timestwo_mex(len_in, in_str);
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
