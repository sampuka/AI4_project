#include "UCIEngine.hpp"

#include <functional>

class MinimaxEngine : public UCIEngine
{
public:
    MinimaxEngine()
    {
        engine_name = "Minimax Engine";
        engine_author = "Mathias, Mathias, Martin og Maly";

        start();
    }

    MoveList movelist;

    void think() override
    {
        // Default white
        int turn = 1;
        if(board.get_turn() == Color::Black)
            turn = -1;

        std::uniform_int_distribution<std::uint8_t> dist(0,1);

        const std::function<void(BoardTree&)> minimax = [&](BoardTree &base)
        {
            if (base.expanded && (base.nodes.size() != 0))
            {
                for (BoardTree &node : base.nodes)
                {
                    minimax(node);
                }

                if (base.board.get_turn() == Color::White)
                {
                    double eval = -1000000;
                    Move best;

                    for (const BoardTree &node : base.nodes)
                    {
                        if (
                                (node.evaluation > eval) ||
                                (node.evaluation == eval && dist(eng) == 1)
                           )
                        {
                            eval = node.evaluation;
                            best = node.move;
                        }
                    }

                    base.evaluation = eval;
                    base.bestmove = best;
                }
                else
                {
                    double eval = 1000000;
                    Move best;

                    for (const BoardTree &node : base.nodes)
                    {
                        if (
                                (node.evaluation < eval) ||
                                (node.evaluation == eval && dist(eng) == 1)
                           )
                        {
                            eval = node.evaluation;
                            best = node.move;
                        }
                    }

                    base.evaluation = eval;
                    base.bestmove = best;
                }
            }
            else
            {
                base.board.get_moves(movelist);
                movelist.is_checkmate = base.is_checkmate;
                movelist.is_stalemate = base.is_stalemate;
                base.evaluation = base.board.adv_eval(movelist);
                /*
                if (movelist.is_stalemate)
                {
                    std::cout << "Evaluating stalemate due to repetition: " << base.evaluation << std::endl;
                }
                */
            }

            return;
        };

        // Create tree structure
        BoardTree root(board);

        std::chrono::duration<double, std::milli> previous_ply(0);
        std::chrono::duration<double, std::milli> last_ply(0);
        int ply = 1;

        std::uint64_t time_left = w_time;
        std::uint64_t time_inc = w_inc;
        if (board.get_turn() == Color::Black)
        {
            time_left = b_time;
            time_inc = b_inc;
        }

        std::uint64_t max_time = std::min(time_inc + time_left/4, std::uint64_t{30000});
        std::uint64_t exp_time = 0;

        while ((max_time - time_spent > exp_time) && (ply <= 4))
        {
            auto tp = std::chrono::high_resolution_clock::now();
            root.expand(movelist, z_list, ply);
            minimax(root);
            std::chrono::duration<double> dur = std::chrono::high_resolution_clock::now() - tp;

            bestmove = root.bestmove;
            evaluation = root.evaluation*turn;

            if (evaluation > 150)
            {
                break;
            }

            ply++;
            previous_ply = last_ply;
            last_ply = dur;

            exp_time = std::min(static_cast<double>(last_ply.count()/previous_ply.count()), double{30})*last_ply.count();
        }

        //std::cout << layer << ' ' << last_layer.count() << ' ' << previous_layer.count() << std::endl;

        /*
        std::cout << "About to move " << bestmove.longform() << std::endl;
        std::cout << root.nodes.size() << std::endl;
        std::cout << evaluation << std::endl;

        MoveList m2;
        BoardTree test(board, bestmove);
        auto z2 = z_list;
        z2.push_back(test.board.get_zobrist());
        test.board.get_moves(m2, z2, false);
        std::cout << int{m2.size()} << std::endl;
        std::cout << m2.is_checkmate << std::endl;
        std::cout << m2.is_stalemate << std::endl;
        std::cout << test.board.adv_eval(m2) << std::endl;
        */

        // End of function
        thinking = false;
    }
};

int main()
{
    MinimaxEngine engine;

    return 0;
}
