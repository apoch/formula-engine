#pragma once



enum ResultCode {
	RESULT_CODE_OK,
	RESULT_CODE_SYNTAX_ERROR,
	RESULT_CODE_MISSING_DEFINITION,
};

struct Result {
	ResultCode code;
	double     value  = 0.0;
	double     value2 = 0.0;
};

struct ListResult {
	ResultCode code;
	std::vector<double> values;
};


struct IFormulaContext {
	virtual Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const = 0;
	virtual ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const = 0;
};

struct IScopeContext {
	virtual const IFormulaContext * ResolveScope(unsigned token) const = 0;
};


struct ITerminalEvaluator {
	virtual ~ITerminalEvaluator() { }
	virtual Result Evaluate(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex) const = 0;
};




class Formula {
public:			// Construction and destruction
	Formula() { }
	~Formula();

public:			// Move semantics
	Formula(Formula && other);
	Formula & operator = (Formula && other);

public:			// Friendships
	friend class FunctionRandom;
	friend class FunctionSumOfList;
	friend class FunctionVector;

public:			// Enumerations
	enum Operator {
		OPERATOR_ADD,
		OPERATOR_SUBTRACT,
		OPERATOR_MULTIPLY,
		OPERATOR_DIVIDE,
		OPERATOR_ERROR
	};

public:			// Setup interface
	void Push(double literalValue);
	void Push(ITerminalEvaluator * evaluator);			// Takes ownership
	void Push(const ITerminalEvaluator & evaluator);	// Does not take ownership
	void Push(Operator op);
	void Push(unsigned scope, unsigned token);

public:			// Evaluation interface
	Result Evaluate(const IFormulaContext * context) const;

private:		// Internal helpers
	Result EvaluateFunction(const IFormulaContext * context, unsigned * pindex) const;
	Result EvaluateSubexpression(const IFormulaContext * context, unsigned * pindex) const;
	Result EvaluateTerminal(const IFormulaContext * context, unsigned index) const;

private:		// Internal helper structures
	struct Term {
		Term() { }
		Term(Term && other);
		Term & operator = (Term && other);

		enum Flags {
			// Mutually exclusive type flags
			FLAG_IS_LITERAL		= 1 << 0,
			FLAG_IS_EVALUATOR	= 1 << 1,
			FLAG_IS_OPERATOR	= 1 << 2,
			FLAG_IS_TOKEN		= 1 << 3,

			// Ownership semantics
			FLAG_OWNS_MEMORY	= 1 << 16,
		};

		union PayloadUnion {
			double				 literalValue;
			ITerminalEvaluator * evaluator;
			Operator			 op;

			struct ScopedToken {
				unsigned scope;
				unsigned token;
			} scopedToken;
		} payload;

		unsigned flags;
	};

private:		// Internal state
	std::vector<Term> m_terms;
};


