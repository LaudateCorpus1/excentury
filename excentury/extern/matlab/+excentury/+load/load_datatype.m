function map = load_datatype(varargin)
% excentury.load.LOAD_DATATYPE: Create loading definition
%
% If no parameters are provided then this function returns
% a dictionary containing the functions already created.
%
% To create a function you must provide 3 arguments:
%
%     xcload = @excentury.load.load
%     excentury.load.load_datatype('Line', { ...
%         xcload('$a', '{"S", "Point"}'), ...
%         xcload('$b', '{"S", "Point"}'), ...
%         'loaded_obj = Line($a.x, $a.y, $b.x, $b.y);'
%     });
% 
% The above example declares the definition for loading an object
% with classname 'Line'. To load it, we need to create an object from
% information that we will encounter. The objects to be encounted
% can be found in a file with the excentury format.
%
% You must use the function excentury.load.load in order to load read
% into a variable. In above example we load a structure 'Point' into
% the variable `a`. This assumes however that the definition to load
% a 'Point' has already been provided. After all the data has been
% read now it remains to build the object. This object needs to be
% placed into `loaded_obj`. This is a special keyword and must be used.
% All read variables declared must have a dollar sign.
%
    persistent comm_dump;
    if isempty(comm_dump)
        comm_dump = containers.Map;
    end
    if nargin == 0
        map = comm_dump;
        return
    end
    obj = varargin{1};
    if isKey(comm_dump, obj)
        map = comm_dump;
        return
    end
    content = [varargin{2}{:}];
    vars = regexp(content, '\$\w*', 'match');
    for i=1:numel(vars)
        item = vars{i};
        content = strrep(content, item, sprintf('dict(''%s'')', item(2:end)));
    end
    comm_dump(obj) = @load_func;
    function loaded_obj = load_func(interface, defs) %#ok<STOUT,INUSD>
        dict = containers.Map; %#ok<NASGU>
        eval(content);
    end
    map = comm_dump;
end
