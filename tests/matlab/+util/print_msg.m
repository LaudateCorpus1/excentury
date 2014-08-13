% util.PRINT_MSG was generated on Sat Jan 04, 2014 08:39:28 PM by xcpp 
% 
%     Print a message to the standard error stream.
% 
%     parameters:
% 
%       `msg`: the message to be printed.
%     
function varargout = print_msg(msg, varargin)
    tdump = excentury.dump.textdumper;
    tdump.dump(msg, 'msg', {'W'});
    in_str = tdump.close;
    len_in = length(in_str);
    [~, out_str] = util.print_msg_mex(len_in, in_str);
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
