function [precision, recall, f] = f_score(classes, predictions)

% precision = true positives / (true positives + false positives)
% fraction of the predicted that were correct


% recall = true positives / (true positives + false negatives)
% fraction of the actual values that were correct
    m = confusionmat(classes, predictions);
    r = diag(m) ./ sum(m,1)';
    recall = r(2); % only store the recall for the second class
    p = diag(m) ./ sum(m,2);
    precision = p(2);
    f = 2 * precision * recall / (precision + recall);
end
