#include "PieceQueue.h"

#include "PieceFactory.h"
#include "system/GraphicsContext.h"

#include <array>
#include <algorithm>
#include <assert.h>


std::array<Piece::Type, Piece::allTypes.size()> possible_pieces = Piece::allTypes;

PieceQueue::PieceQueue(unsigned displayed_piece_count)
    : displayed_piece_count(displayed_piece_count)
{
    generate_pieces();

    size_t i = 0;
    for(const auto p : Piece::allTypes) {
        piece_storage[i] = PieceFactory::make_uptr(p);
        i++;
    }
}

Piece::Type PieceQueue::next()
{
    Piece::Type piece = piece_queue.front();
    piece_queue.pop_front();
    if (piece_queue.size() <= displayed_piece_count)
        generate_pieces();

    assert(piece_queue.size() > displayed_piece_count);
    return piece;
}

void PieceQueue::generate_pieces()
{
    std::random_shuffle(possible_pieces.begin(), possible_pieces.end());

    for (const auto p : possible_pieces)
        piece_queue.push_back(p);
}

void PieceQueue::draw(GraphicsContext& gcx, unsigned x, unsigned y)
{
    static const unsigned piece_distance_y = Mino::texture_size_px * 4 + 10 /* padding */;

    for (unsigned i = 0; i < displayed_piece_count; i++) {
        piece_storage.at(static_cast<size_t>(piece_queue.at(i)))
            ->draw(gcx, x, y + Mino::texture_size_px + i * piece_distance_y);
    }
}


