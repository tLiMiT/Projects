% MATLAB Sudoku Solver
% Tim Liming
%
%

function SudokuGUI

    %% Create Figure

    s = figure('Name', 'Sudoku Solver', ...
        'Units', 'pixels', ...
        'Position', [500 200 700 500], ...
        'NumberTitle', 'off', ...
        'Toolbar', 'none' ...
        );

    %% Create Text Partition

    % Panel for text
    p1 = uipanel('Parent', s, 'Title', ' - Sudoku Text Input - ', ...
        'Units', 'pixels', ...
        'Position', [50 50 300 400], ...
        'BackgroundColor', 'white' ...
        );
    
    % Text Box
    tb = uicontrol(p1, 'Style', 'edit', ...
        'Position', [15 75 265 300], ...
        'BackgroundColor', 'red', ...
        'Callback', {} ...
        );

    % Clear Text Button
    cltb = uicontrol(p1, 'Style', 'pushbutton', ...
        'String', 'Clear', ...
        'Position', [15 25 265 30], ...
        'Callback', {@clearText} ...
        );
        
    %% Create Board Partition
    
    % Panel for board
    p2 = uipanel('Parent', s, 'Title', ' - Sudoku board - ', ...
        'Units', 'pixels', ...
        'Position', [375 150 300 300], ...
        'BackgroundColor', 'white' ...
        );
    
    % Board Box
    bb = uicontrol(p2, 'Style', 'text', ...
        'String', 'boardStr', ...
        'Position', [22 21 250 250], ...
        'BackgroundColor', 'red' ...
        );

    %% Solve Sudoku Button

    solb = uicontrol(s, 'Style', 'pushbutton', ...
        'String', 'Solve', ...
        'Position', [425 50 200 60], ...
        'Callback', {@solveBoard} ...
        );

    %% Callbacks
    
    % Set the cell value
    function setCell(source, eventdata)
        set(source, str2num(get(source, 'Value')));
    end

    % Clears every cell for a new puzzle
    function clearGrid(source, eventdata)
        % clear every cell
        for (x = 1:1:9)
            for (y = 1:1:9)
                set(cells(x,y), 'Value', 0);
            end
        end
    end

    % Solve the given Sudoku puzzle
    function solveGrid(source, eventdata)
        % build grid 
        grid = [];
        for (x = 1:1:9)
            for (y = 1:1:9)
                if get(cells(x,y), 'Value') == 0
                    grid(x,y) = 0;
                else
                    grid(x,y) = get(cells(x,y), 'Value');
                end
            end
        end
        
    end
end