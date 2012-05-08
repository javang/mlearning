function [dtest] = get_with_same_double_values(test, training)
%{
  For many algorithms in MATLAB  a nominal variable must be converted
  to a numerical matrix. When presenting a test set to the algorithm,
  a numerical matrix is also required. But the conversion must assign
  to the categories in the test set the same number that wass assigned
  to them in the training set. The MATLAB double() function does not 
  do that. 

  This function performs the assignment. It is only done for nominal
  features
  test - nominal variable
  training - nominal variable with the training data
%}
dtest = zeros(size(test));
varnames = training.Properties.VarNames;
m = size(varnames,2);
for i = 1:m
    name = char(varnames(i));
    % nominal variables, assign the corresponding number from the classes
    % in the training variable
    if(isa(training.(name), 'nominal'))
        varlevels = getlevels(training.(name));
        n = size(varlevels, 2);
        for j = 1:n
            % this applies because the order of the levels 
            % is the number in the matrix after converting to double:
            % level(j) has index j

            dtest(test.(name) == varlevels(j), i) = j;
        end
    else
        % just copy
        dtest(:,i) = test.(name);
    end
end

end