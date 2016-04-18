#pragma once

typedef struct Result (*FTerminalEvaluator)(const struct IFormulaContext * context, const class Formula & termSource, unsigned * pindex);


FTerminalEvaluator GetFunctionEvaluatorByName (const char str[]);


