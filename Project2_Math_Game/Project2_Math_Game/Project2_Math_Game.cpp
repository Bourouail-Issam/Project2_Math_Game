
#include <iostream>
#include <typeinfo>
using namespace std;

enum EnQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum EnOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion {
	int Number1 = 0;
	int Number2 = 0;
	EnQuestionLevel QuestionLevel;
	EnOperationType TypeOperation;
	short RightAnswer = 0;
	short UserAnwser = 0;
	bool AnwserResult = false;
};
struct stQuizz {
	stQuestion ListQuestion[100];
	short NumberQuestion = 0;
	EnQuestionLevel QuestionLevel;
	EnOperationType TypeO;
	short NumberRightAnwser = 0;
	short NumberWrongAnwser = 0;
	bool IsPass = false;
};
void ResetScreen() {
	system("cls");
	system("color 0F");
}
int RandomNumber(int From , int To) {
	int RandomNum = (rand() % (To - From + 1)) + From;
	return RandomNum;
}
short HowManyQuestion() {
	short NumberQuestion;
	do	{
		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberQuestion;
	} while (NumberQuestion < 1 || NumberQuestion > 100);
	return NumberQuestion;
}
EnQuestionLevel WhatIsQuestionLevel() {
	short NumberQuestion;
	do {
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> NumberQuestion;
	} while (NumberQuestion < 1 || NumberQuestion > 4);
	return (EnQuestionLevel)NumberQuestion;
}
EnOperationType WhatIsQuestionType() {
	short NumberQuestion;
	do {
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> NumberQuestion;
	} while (NumberQuestion < 1 || NumberQuestion > 5);
	return (EnOperationType)NumberQuestion;
}
int CalcRightAnwser(int Number1 , int Number2, EnOperationType TypeO) {
	switch (TypeO)
	{
	case EnOperationType::Add:
		return Number1 + Number2;
	case EnOperationType::Sub:
		return Number1 - Number2;
	case EnOperationType::Mul:
		return Number1 * Number2;
	case EnOperationType::Div:
		return Number1 / Number2;
	}
}
stQuestion GenerateQuestion(EnQuestionLevel QuestionLevel, EnOperationType TypeO) {
	stQuestion Question;

	if (QuestionLevel == EnQuestionLevel::Mix) 
		QuestionLevel = (EnQuestionLevel)RandomNumber(1, 3);
	if (TypeO == EnOperationType::MixOp) 
		TypeO = (EnOperationType)RandomNumber(1, 4);

	Question.TypeOperation = TypeO;

	switch (QuestionLevel) {
	case Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.RightAnswer = CalcRightAnwser(Question.Number1, Question.Number2, Question.TypeOperation);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case Med:
		Question.Number1 = RandomNumber(1, 100);
		Question.Number2 = RandomNumber(1, 100);
		Question.RightAnswer = CalcRightAnwser(Question.Number1, Question.Number2, Question.TypeOperation);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case Hard:
		Question.Number1 = RandomNumber(1, 310);
		Question.Number2 = RandomNumber(1, 310);
		Question.RightAnswer = CalcRightAnwser(Question.Number1, Question.Number2, Question.TypeOperation);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
}
void GenerateQuizzzQuestions(stQuizz& Quizz) {
	for (short NumeroQuestion = 0;  NumeroQuestion < Quizz.NumberQuestion ; NumeroQuestion++) {
		Quizz.ListQuestion[NumeroQuestion] = GenerateQuestion(Quizz.QuestionLevel,Quizz.TypeO);
	}
}
short ReadAnwserUser() {
	short Number;
	cin >> Number;
	return Number;
}
char GetOperation(EnOperationType TypeO) {
	char tOp[4] = { '+','-','*','/' };
	return tOp[(int)TypeO - 1];
}
void PrintQuesion(stQuizz& Quizz, short NumeroQuestion) {
	cout << "\nQuestion [" << NumeroQuestion-1 << "/" << Quizz.NumberQuestion << "]\n\n";
	cout << Quizz.ListQuestion[NumeroQuestion].Number1 << endl;
	cout << Quizz.ListQuestion[NumeroQuestion].Number2 << " " << GetOperation(Quizz.ListQuestion[NumeroQuestion].TypeOperation) << endl;
	cout << "-----------\n";
}
void CorrectQuestionAnwser(stQuizz & Quizz , short NumeroQuestion) {

	if (Quizz.ListQuestion[NumeroQuestion].RightAnswer != Quizz.ListQuestion[NumeroQuestion].UserAnwser) {
		Quizz.NumberWrongAnwser++;
		Quizz.ListQuestion[NumeroQuestion].AnwserResult = false;
		cout << "Wrong Answer :-(\n\n";
		cout << "The Right answer is : " << Quizz.ListQuestion[NumeroQuestion].RightAnswer << endl;
	}
	else {
		Quizz.NumberRightAnwser++;
		Quizz.ListQuestion[NumeroQuestion].AnwserResult = true;
		cout << "\nRight Answer :(-\n\n";
	}
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz) {

	for (short NumeroQuestion = 0; NumeroQuestion < Quizz.NumberQuestion; NumeroQuestion++) {
		PrintQuesion(Quizz, NumeroQuestion);
		Quizz.ListQuestion[NumeroQuestion].UserAnwser = ReadAnwserUser();
		CorrectQuestionAnwser(Quizz, NumeroQuestion);
	}
	Quizz.IsPass = (Quizz.NumberRightAnwser >= Quizz.NumberWrongAnwser);
}
string GetFinalResultsText(bool IsPass){
	if (IsPass)
		return "PASS :-)";
	else
		return "Fail :-(";
}
string LevelToString(EnQuestionLevel Level){
	string ListLevel[4] = { "Easy","Med","Hard","Mix" };
	return ListLevel[(int)Level - 1];
}
string TypeOperationToString(EnOperationType TypeO) {
	switch (TypeO)
	{
	case EnOperationType::Add:
		return "Add";
	case EnOperationType::Sub:
		return "Sub";
	case EnOperationType::Mul:
		return "Mul";
	case EnOperationType::Div:
		return "Div";
	case EnOperationType::MixOp:
		return "Mix";
	}
}
void PrintQuizzResults(stQuizz Quizz){
	cout << "\n____________________________________\n\n";
	cout << "Final Result is " << GetFinalResultsText(Quizz.IsPass) <<endl;
	cout << "\nNumber of Question : " << Quizz.NumberQuestion ;
	cout << "\nQuestion Level : " << LevelToString(Quizz.QuestionLevel);
	cout << "\nOpType         : " << TypeOperationToString(Quizz.TypeO);
	cout << "\nNumber of Right Answer : " << Quizz.NumberRightAnwser;
	cout << "\nNumber of wrong Answer : " << Quizz.NumberWrongAnwser << endl;
	cout << "\n_____________________________________\n\n";
}
void PlayMathGame() {
	stQuizz Quizz;
	Quizz.NumberQuestion = HowManyQuestion();
	Quizz.QuestionLevel = WhatIsQuestionLevel();
	Quizz.TypeO = WhatIsQuestionType();

	GenerateQuizzzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}
void StartGame() {
	char PlayAgain = 'y';
	do {
		ResetScreen();
		PlayMathGame();
		cout << "Do you want to play again? Y/N?\n : ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}
