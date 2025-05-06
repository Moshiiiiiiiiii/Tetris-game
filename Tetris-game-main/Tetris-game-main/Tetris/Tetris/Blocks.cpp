#include "block.h" // Includes the base Block class
#include "position.h" // Includes the Position class for defining cell positions

// LBlock: Represents the "L" shaped Tetris block
class LBlock : public Block
{
public:
    LBlock()
    {
        id = 1; // Unique ID for the LBlock
        // Define the block's cells for each of its 4 rotation states
        cells[0] = { Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0) };
        cells[3] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1) };
        Move(0, 3); // Adjust the block's initial position
    }
};

// JBlock: Represents the "J" shaped Tetris block
class JBlock : public Block
{
public:
    JBlock()
    {
        id = 2; // Unique ID for the JBlock
        cells[0] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) };
        cells[3] = { Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1) };
        Move(0, 3); // Adjust the block's initial position
    }
};

// IBlock: Represents the "I" shaped Tetris block
class IBlock : public Block
{
public:
    IBlock()
    {
        id = 3; // Unique ID for the IBlock
        cells[0] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) };
        cells[1] = { Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) };
        cells[2] = { Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) };
        cells[3] = { Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) };
        Move(-1, 3); // Adjust the block's initial position
    }
};

// OBlock: Represents the "O" (square) shaped Tetris block
class OBlock : public Block
{
public:
    OBlock()
    {
        id = 4; // Unique ID for the OBlock
        cells[0] = { Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) };
        Move(0, 4); // Adjust the block's initial position
    }
};

// SBlock: Represents the "S" shaped Tetris block
class SBlock : public Block
{
public:
    SBlock()
    {
        id = 5; // Unique ID for the SBlock
        cells[0] = { Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) };
        cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) };
        cells[2] = { Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) };
        cells[3] = { Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) };
        Move(0, 3); // Adjust the block's initial position
    }
};

// TBlock: Represents the "T" shaped Tetris block
class TBlock : public Block
{
public:
    TBlock()
    {
        id = 6; // Unique ID for the TBlock
        cells[0] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) };
        cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1) };
        Move(0, 3); // Adjust the block's initial position
    }
};

// ZBlock: Represents the "Z" shaped Tetris block
class ZBlock : public Block
{
public:
    ZBlock()
    {
        id = 7; // Unique ID for the ZBlock
        cells[0] = { Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) };
        cells[1] = { Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) };
        cells[2] = { Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) };
        cells[3] = { Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) };
        Move(0, 3); // Adjust the block's initial position
    }
};
