clear all

% If you are using a class that you did not create
% then make the call to excentury.load_datatype
% and specify how to load the object.
xc_load = @excentury.load.load;
excentury.load.load_datatype('Point', { ...
    xc_load('$x', '{"R", "8"}'), ...
    xc_load('$y', '{"R", "8"}'), ...
    'loaded_obj = Point($x, $y);'
});
% A class may write the above definitions inside
% the static function enable_excentury and this
% function must be called so that excentury may
% learn its definition.
Line.enable_excentury;

var = excentury.load_file('tmp.xc');
fid = fopen('tmp_ml_out.txt', 'w');
for key=var.keys()
    fprintf(fid, '%s = ', key{1});
    fprintf(fid, evalc('disp(var(key{1}))'));
end
fclose(fid);
