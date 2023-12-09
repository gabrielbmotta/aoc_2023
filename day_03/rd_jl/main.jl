using DelimitedFiles
using Statistics

# Read the file
file = joinpath("c:/Users/rubendorfel/git/aoc_2023/","day_03","rd_jl", "test.txt")

lines = readdlm(file)

function create_board(lines)
    # Split the strings
    arr_list = [collect(str) for str in lines]
    return hcat(arr_list...)
end

function iterate_throug_board(board)
    ncols, nrows = size(board)
    entries = []
    for irow in 1:nrows
        for icol in 1:ncols
            if check_surrounding(board, icol, irow)
                entries = append!(entries,get_entry(board, icol, irow))
            else
                entries = append!(entires,'.')
            end
        end
    end
    print(join(entries))
end

function get_entry(board, col, row)
    try 
        return board[col, row]
    catch
        return "."
    end
end

function check_surrounding(board, icol, irow)
    if get_entry(board, icol, irow) === "."
        return false
    else
        pairs = [(icol-1, irow), (icol-1, irow-1), (icol, irow-1), (icol+1, irow), (icol+1, irow+1), (icol, irow+1)]
        for pair in pairs
            if get_entry(board, pair[1], pair[2]) !== "."
                return true
            end
        end
    end
end
board = create_board(lines)
iterate_throug_board(board)

