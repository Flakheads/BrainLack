#include "program_tree.h"

namespace bf {

	Monad::Monad(const std::vector<std::shared_ptr<Node> >& contained)
		: modStack(false), constant(true), val(0), containedOps(contained) {

		for (std::shared_ptr<Node> node : contained) {
			if (node->modifiesStack()) {
				modStack = true;
			}
			if (!node->isConstant()) {
				constant = false;
				val = 0;
			}
			if (constant) {
				val += node->getValue();
			}
		}
	}

	std::shared_ptr<Node> createNilad(char brace) {
		switch (brace) {
			case '(':
			case ')':
				return std::shared_ptr<Node>(new PlusOne);
			case '[':
			case ']':
				return std::shared_ptr<Node>(new StackHeight);
			case '{':
			case '}':
				return std::shared_ptr<Node>(new Pop);
			case '<':
			case '>':
				return std::shared_ptr<Node>(new StackSwap);
		}
		return std::shared_ptr<Node>(nullptr);
	}

	std::shared_ptr<Node> createMonad(char brace, const std::vector<std::shared_ptr<Node> >& contained) {
		switch (brace) {
			case '(':
			case ')':
				return std::shared_ptr<Node>(new Push(contained));
			case '[':
			case ']':
				return std::shared_ptr<Node>(new Negative(contained));
			case '{':
			case '}':
				return std::shared_ptr<Node>(new Loop(contained));
			case '<':
			case '>':
				return std::shared_ptr<Node>(new Zero(contained));
		}
		return std::shared_ptr<Node>(nullptr);
	}

}
