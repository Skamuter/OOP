#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Box;

class Ball {
public:
    explicit Ball(std::string color) : color_(std::move(color)) {}
    ~Ball();

    Ball(const Ball&) = delete;
    Ball& operator=(const Ball&) = delete;

    const std::string& color() const { return color_; }
    Box* box() const { return box_; }
    bool in_box() const { return box_ != nullptr; }

    void report() const;

private:
    friend class Box;
    std::string color_;
    Box* box_ = nullptr;
};

class Box {
public:
    explicit Box(std::string name) : name_(std::move(name)) {}
    ~Box() {
        for (Ball* ball : balls_) ball->box_ = nullptr;
    }

    Box(const Box&) = delete;
    Box& operator=(const Box&) = delete;

    const std::string& name() const { return name_; }

    void put(Ball& ball) {
        if (ball.box_ == this) return;
        if (ball.box_ != nullptr) ball.box_->take_out(ball); 
        balls_.push_back(&ball);
        ball.box_ = this;
    }

    void take_out(Ball& ball) {
        auto it = std::find(balls_.begin(), balls_.end(), &ball);
        if (it == balls_.end()) return;
        balls_.erase(it);
        ball.box_ = nullptr;
    }

    void report() const {
        std::cout << "Box \"" << name_ << "\": ";
        if (balls_.empty()) {
            std::cout << "empty\n";
            return;
        }
        for (std::size_t i = 0; i < balls_.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << balls_[i]->color();
        }
        std::cout << '\n';
    }

private:
    std::string name_;
    std::vector<Ball*> balls_;
};

Ball::~Ball() {
    if (box_ != nullptr) box_->take_out(*this);
}

void Ball::report() const {
    std::cout << "Ball " << color_ << ": ";
    if (box_ != nullptr)
        std::cout << "in box \"" << box_->name() << "\"\n";
    else
        std::cout << "not in a box\n";
}

int main() {
    Ball red("red"), green("green"), blue("blue"), yellow("yellow"), white("white");
    Box left("left"), right("right");

    left.put(red);
    left.put(green);
    right.put(blue);
    right.put(yellow);

    std::cout << "--- Initial distribution ---\n";
    left.report();
    right.report();
    for (const Ball* b : { &red, &green, &blue, &yellow, &white }) b->report();

    std::cout << "\n--- Move green to the right box ---\n";
    right.put(green);
    left.report();
    right.report();
    green.report();

    std::cout << "\n--- Take blue out of the right box ---\n";
    right.take_out(blue);
    right.report();
    blue.report();

    return 0;
}
