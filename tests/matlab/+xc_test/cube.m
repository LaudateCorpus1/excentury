% xc_test.CUBE generated on Sat Aug 16, 2014 03:45:55 PM by xcpp
% 
%     cube an integer
% 
%     parameters:
% 
%       `x`: integer to be cubed.
%     
function varargout = cube(x, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(x, 'x', {'I', '4'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = xc_test.cube_mex(len_in, in_str);
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
