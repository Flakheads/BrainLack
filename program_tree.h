#ifndef __program_tree_h_
#define __program_tree_h_

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
	};

	class StackHeight : public Node {
		public:
			bool modifiesStack() const { return false; };
			bool isConstant() const { return false; };
			// since StackHeight is not constant getValue() doesn't matter
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '['; };
			char getClosingBrace() const { return ']'; };
	};

	class Pop : public Node {
		public:
			bool modifiesStack() const { return true; };
			bool isConstant() const { return false; };
			// since Pop is not constant getValue() doesn't matter
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '{'; };
			char getClosingBrace() const { return '}'; };
	};

	class StackSwap : public Node {
		public:
			bool modifiesStack() const { return true; };
			bool isConstant() const { return true; };
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '<'; };
			char getClosingBrace() const { return '>'; };
	};

	class Monad : public Node {
		public:
			void addOperation(const Node& op);
	};

	class Push : public Monad {
		public:
			bool modifiesStack() const { return true; };
			bool isConstant() const;
			int getValue() const;
			char getOpeningBrace() const { return '('; };
			char getClosingBrace() const { return ')'; };
	};

	class Negative : public Monad {
		public:
			bool modifiesStack() const;
			bool isConstant() const;
			int getValue() const;
			char getOpeningBrace() const { return '['; };
			char getClosingBrace() const { return ']'; };
	};

	class Loop : public Monad {
		public:
			bool modifiesStack() const;
			bool isConstant() const { return false; };
			// since Loop is not constant getValue() doesn't matter
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '{'; };
			char getClosingBrace() const { return '}'; };
	};

	class Zero : public Monad {
		public:
			bool modifiesStack() const;
			bool isConstant() const { return true; };
			int getValue() const { return 0; };
			char getOpeningBrace() const { return '<'; };
			char getClosingBrace() const { return '>'; };
	};
}
#endif//__program_tree_h_
