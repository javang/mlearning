function test_suite = tests_for_classes_related_to_trees
initTestSuite;

    function test_parent
        clear;
        root = DataNode;
        t = Tree(root);
        t.root.data = [2,4];
        n = DataNode;
        t.root.add_child(n);
        t.root.first_child.data = [2,3,45];
        assertEqual(t.root.first_child.parent.data, t.root.data);    
    

    function test_depth_fist
        % test if the tree is search depth first
        clear;
        A = BinaryDataNode;
        A.data = 1;
        B = BinaryDataNode;
        B.data = 2;
        A.left = B;
        C = BinaryDataNode;
        C.data = 7;
        A.right = C;
        D = BinaryDataNode;
        D.data = 3;
        B.left = D;
        E = BinaryDataNode;
        E.data = 8;
        B.right = E;
        F = BinaryDataNode;
        F.data = 30;
        C.left = F;
        G = BinaryDataNode;
        G.data = 19;
        C.right = G;
        nodes = [];
        nodes = depth_first(A,nodes);
        assertEqual([nodes.data],[3 8 2 30 19 7 1])
    
    function test_tree_node
        clear;
        root = TreeNode;
        x = TreeNode;
        root.add_child(x);
        y = TreeNode;
        root.add_child(y);
        assertEqual(y.parent, x.parent);
        assertEqual(x.next_sibling, y);
    
    function test_get_children
        clear all;
        root = DataNode;
        x = DataNode;
        x.data =3;
        y = DataNode;
        y.data = 2;
        z = DataNode;
        z.data = 1;
        root.add_child(x);
        root.add_child(y);
        root.add_child(z);
        ch = root.get_children();
        assertEqual([ch.data],[3 2 1]);

    function test_trivial_decision_tree
        clear all;
        training = dataset('File','golf_trivial.csv','delimiter',',');
        are_categorical = [true true true true true];
        training = dataset_to_nominal(training, are_categorical);
        Y = training.Play;
        ddata = double(training);
        expected = ddata(:,5);
        ddata = ddata(:,1:4);
        T = DecisionTree;
        T.train(ddata, Y, are_categorical);
        % use as test the training data
        predictions = T.predict(ddata);
        assertEqual(predictions, expected);
        
    function test_decision_tree
        clear all;
        training = dataset('File','golf.csv', 'delimiter',',');
        are_categorical = [true true true true true];
        training = dataset_to_nominal(training, are_categorical);
        Y = training.Play;
        training.Play = [];
        ddata = double(training);
        T = DecisionTree;
        T.train(ddata, Y, are_categorical);      

        test = dataset('File', 'golf_test.csv', 'delimiter', ',');
        test = dataset_to_nominal(test, are_categorical);
        dtest = get_with_same_double_values(test, training);
        assertEqual(dtest,[3 3 2 2; 1 3 1 1; 3 1 2 2; 1 3 2 2; ...
                            2 2 1 2]);
        predictions = T.predict(dtest);
        assertEqual(predictions,[2 2 2 2 1]');

    function test_decision_tree_continuous
        clear all;
        training = dataset('File','golf_continuous.csv', 'delimiter',',');
        are_categorical = [true true false true true];
        training = dataset_to_nominal(training, are_categorical);
        Y = training.Play;
        training.Play = [];
        ddata = double(training);
        T = DecisionTree;
        % T.gain_measure = 'entropy'  % the test is with 'gini', but also
        % works with entropy
        T.train(ddata, Y, are_categorical);      
        test = dataset('File', 'golf_test_continuous.csv', 'delimiter', ',');
        test = dataset_to_nominal(test, are_categorical);
        dtest = get_with_same_double_values(test, training);
        predictions = T.predict(dtest);
        assertEqual(predictions,[2 2 2 2 1]');


        