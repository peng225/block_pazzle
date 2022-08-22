#include <iostream>
#include <memory>
#include <solver.h>

int main() {
    auto s = std::make_shared<Solver>(6, 10);
    std::vector<char> body = {'a', ' ',
                              'a', ' ', 
                              'a', 'a',
                              'a', ' '};
    auto piece = std::make_shared<Piece>(2, 4, body);
    s->addPiece(piece);

    body = {'b', 'b', 'b', 'b',
            'b', ' ', ' ', ' '};
    piece = std::make_shared<Piece>(4, 2, body);
    s->addPiece(piece);

    body = {' ', ' ', 'c',
            ' ', 'c', 'c',
            'c', 'c', ' '};
    piece = std::make_shared<Piece>(3, 3, body);
    s->addPiece(piece);

    body = {' ', 'd', 'd',
            ' ', 'd', ' ',
            'd', 'd', ' '
    };
    piece = std::make_shared<Piece>(3, 3, body);
    s->addPiece(piece);

    body = {' ', ' ', 'e',
            'e', 'e', 'e',
            ' ', ' ', 'e'};
    piece = std::make_shared<Piece>(3, 3, body);
    s->addPiece(piece);

    body = {'f', 'f', 'f', 'f', 'f'};
    piece = std::make_shared<Piece>(5, 1, body);
    s->addPiece(piece);

    body = {'g', 'g', 'g', ' ',
            ' ', ' ', 'g', 'g'};
    piece = std::make_shared<Piece>(4, 2, body);
    s->addPiece(piece);

    body = {'h', 'h', 'h',
            ' ', 'h', 'h'};
    piece = std::make_shared<Piece>(3, 2, body);
    s->addPiece(piece);

    body = {'i', 'i', ' ',
            ' ', 'i', 'i',
            ' ', 'i', ' '};
    piece = std::make_shared<Piece>(3, 3, body);
    s->addPiece(piece);

    body = {'j', ' ', ' ',
            'j', ' ', ' ',
            'j', 'j', 'j'};
    piece = std::make_shared<Piece>(3, 3, body);
    s->addPiece(piece);

    body = {' ', 'k', ' ',
            'k', 'k', 'k',
            ' ', 'k', ' '};
    piece = std::make_shared<Piece>(3, 3, body);
    s->addPiece(piece);

    body = {'l', 'l',
            ' ', 'l',
            'l', 'l'};
    piece = std::make_shared<Piece>(2, 3, body);
    s->addPiece(piece);

    s->solve();
    return 0;
}