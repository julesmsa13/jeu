#include <iostream>

class Orientation {
public:
    // Enum representing four cardinal directions
    enum class Direction { North, East, South, West };

    // Constructor initializes the orientation
    Orientation(Direction initial_direction = Direction::North)
        : current_orientation(initial_direction) {}

    // Getter for current orientation
    Direction getOrientation() const {
        return current_orientation;
    }

    // Setter for orientation
    void setOrientation(Direction orientation) {
        current_orientation = orientation;
    }

    // Rotate left (counterclockwise)
    void rotateLeft() {
        current_orientation = static_cast<Direction>((static_cast<int>(current_orientation) + 3) % 4);
    }

    // Rotate right (clockwise)
    void rotateRight() {
        current_orientation = static_cast<Direction>((static_cast<int>(current_orientation) + 1) % 4);
    }

private:
    Direction current_orientation;
};

// Helper function to display the direction as a string
std::string to_string(Orientation::Direction direction) {
    switch (direction) {
    case Orientation::Direction::North: return "North";
    case Orientation::Direction::East:  return "East";
    case Orientation::Direction::South: return "South";
    case Orientation::Direction::West:  return "West";
    default: return "Unknown";
    }
}