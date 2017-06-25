#ifndef __program_tree_h_
#define __program_tree_h_

#include <vector>
#include <memory>

namespace bf {

	class Node {
		public:
			virtual bool modifiesStack() const = 0;
			virtual bool isConstant() const = 0;
			virtual int getValue() const = 0;
			virtual char getOpeningBrace() const = 0;
			virtual char getClosingBrace() const = 0;
	};

	class PlusOne : public Node {
		public:
			bool modifiesStack() const { return false; };
			bool isConstant() const { return true; };
			int getValue() const { return 1; };
			char getOpeningBrace() const { return '('; };
			char getClosingBrace() const { return ')'; };
			friend std::shared_ptr<Node> createNilad(char);
	};

	class StackHeight : public Node {
		public:
			bool modifiesStack() const { return false; };
			bool isConstant() const { return false; };
			// since StackHeight is not constant getValue() doesn't matter
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '['; };
			char getClosingBrace() const { return ']'; };
			friend std::shared_ptr<Node> createNilad(char);
	};

	class Pop : public Node {
		public:
			bool modifiesStack() const { return true; };
			bool isConstant() const { return false; };
			// since Pop is not constant getValue() doesn't matter
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '{'; };
			char getClosingBrace() const { return '}'; };
			friend std::shared_ptr<Node> createNilad(char);
	};

	class StackSwap : public Node {
		public:
			bool modifiesStack() const { return true; };
			bool isConstant() const { return true; };
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '<'; };
			char getClosingBrace() const { return '>'; };
			friend std::shared_ptr<Node> createNilad(char);
	};

	class Monad : public Node {
		bool modStack, constant;
		int val;
		std::vector<std::shared_ptr<Node> > containedOps;

		protected:
			Monad(std::vector<std::shared_ptr<Node> > contained);

		public:
			virtual bool modifiesStack() const { return modStack; };
			virtual bool isConstant() const { return constant; };
			virtual int getValue() const { return val; };
	};

	class Push : public Monad {
		public:
			Push(std::vector<std::shared_ptr<Node> > contained) : Monad(contained) {};

			bool modifiesStack() const { return true; };
			char getOpeningBrace() const { return '('; };
			char getClosingBrace() const { return ')'; };
			friend std::shared_ptr<Node> createMonad(char, const std::vector<std::shared_ptr<Node> >&);
	};

	class Negative : public Monad {
		public:
			Negative(std::vector<std::shared_ptr<Node> > contained) : Monad(contained) {};

			int getValue() const { return -Monad::getValue(); };
			char getOpeningBrace() const { return '['; };
			char getClosingBrace() const { return ']'; };
			friend std::shared_ptr<Node> createMonad(char, const std::vector<std::shared_ptr<Node> >&);
	};

	class Loop : public Monad {
		public:
			Loop(std::vector<std::shared_ptr<Node> > contained) : Monad(contained) {};

			bool isConstant() const { return false; };
			// since Loop is not constant getValue() doesn't matter
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '{'; };
			char getClosingBrace() const { return '}'; };
			friend std::shared_ptr<Node> createMonad(char, const std::vector<std::shared_ptr<Node> >&);
	};

	class Zero : public Monad {
		public:
			Zero(std::vector<std::shared_ptr<Node> > contained) : Monad(contained) {};

			bool isConstant() const { return true; };
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '<'; };
			char getClosingBrace() const { return '>'; };
			friend std::shared_ptr<Node> createMonad(char, const std::vector<std::shared_ptr<Node> >&);
	};

	std::shared_ptr<Node> createNilad(char brace);

	std::shared_ptr<Node> createMonad(char brace, const std::vector<std::shared_ptr<Node> >& contained);
}
#endif//__program_tree_h_
