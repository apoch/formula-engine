#pragma once



enum ResultCode : unsigned {
	RESULT_CODE_OK,
	RESULT_CODE_SYNTAX_ERROR,
	RESULT_CODE_MISSING_DEFINITION,
	RESULT_CODE_TYPE_ERROR,
};

enum ResultType : unsigned {
	RESULT_TYPE_TOKEN,
	RESULT_TYPE_SCALAR,
	RESULT_TYPE_VECTOR2,
};

struct Result {
	Result () {
		type = RESULT_TYPE_SCALAR;
		payload.num.value = 0;
	}

	ResultCode code;
	ResultType type;

	union ResultPayload {
		struct NumericPayload {
			ValueT     value;
			ValueT     value2;
		} num;

		struct TextPayload {
			unsigned   token;
			unsigned   scope;
		} txt;
	} payload;
};

struct ListResult {
	ResultCode code;
	std::vector<ValueT> values;
};


struct IFormulaContext {
	virtual ~IFormulaContext() { }

	virtual Result ResolveNumber(const IFormulaContext & context, unsigned scope, unsigned token) const = 0;
	virtual ListResult ResolveList(const IFormulaContext & context, unsigned scope, unsigned token) const = 0;

	virtual bool ResolveToken (unsigned scope, unsigned token, std::string * out) const {
		ref(scope);
		ref(token);
		ref(out);
		return false;
	}

	virtual const IFormulaContext * ResolveContext (unsigned scope) const {
		ref(scope);
		return const_cast<IFormulaContext *>(this);
	}
};


typedef Result (*FTerminalEvaluator)(const IFormulaContext * context, const class Formula & termSource, unsigned * pindex);




class Formula {
public:			// Construction
	Formula();

	Formula (Formula && other);
	Formula (const Formula & other);

public:			// Assignment
	Formula & operator= (Formula && other);
	Formula & operator= (const Formula & other);

public:			// Enumerations
	enum Operator {
		OPERATOR_ADD,
		OPERATOR_SUBTRACT,
		OPERATOR_MULTIPLY,
		OPERATOR_DIVIDE,
		OPERATOR_ERROR
	};

public:			// Setup interface
	void Push (ValueT literalValue);
	void Push (FTerminalEvaluator evaluator);
	void Push (Operator op);
	void Push (unsigned scope, unsigned token);

public:			// Evaluation interface
	Result Evaluate (const IFormulaContext * context) const;
	Result EvaluateSubexpression (const IFormulaContext * context, unsigned * pindex) const;
	bool EvaluateScopedToken (unsigned index, unsigned * outScope, unsigned * outToken) const;

private:		// Internal helper structures
	struct Term {
		enum Type : unsigned {
			TERM_TYPE_LITERAL,
			TERM_TYPE_EVALUATOR,
			TERM_TYPE_OPERATOR,
			TERM_TYPE_TOKEN,
		} type;

		union PayloadUnion {
			ValueT				 literalValue;
			FTerminalEvaluator   evaluator;
			Operator			 op;

			struct ScopedToken {
				unsigned scope;
				unsigned token;
			} scopedToken;
		} payload;
	};

private:		// Internal state
	unsigned m_termCount;
	Term m_termBuffer[16];

private:		// Shared state
	static unsigned s_evaluationCounter;
public:
	static unsigned GetEvaluationCounter ();
};


