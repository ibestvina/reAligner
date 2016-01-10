#pragma once

class Overlap
{
	int ID_A;
	int ID_B;
	int Shared;
	int Direction_A;
	int Start_A;
	int End_A;
	int Length_A;
	int Direction_B;
	int Start_B;
	int End_B;
	int Length_B;
	float JaccardScore;

public:
	//************************************
	// Method:    Overlap
	// FullName:  Overlap::Overlap
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: int ID_A
	// Parameter: int ID_B
	// Parameter: float JaccardScore
	// Parameter: int Shared
	// Parameter: int Direction_A
	// Parameter: int Start_A
	// Parameter: int End_A
	// Parameter: int Length_A
	// Parameter: int Direction_B
	// Parameter: int Start_B
	// Parameter: int End_B
	// Parameter: int Length_B
	//************************************
	Overlap(int ID_A, int ID_B, float JaccardScore,int Shared, int Direction_A, int Start_A,
		int End_A, int Length_A, int Direction_B, int Start_B, int End_B, int Length_B)
	{
		this->ID_A			= ID_A;
		this->ID_B			= ID_B;
		this->JaccardScore	= JaccardScore;
		this->Shared		= Shared;
		this->Direction_A	= Direction_A;
		this->Start_A		= Start_A;
		this->End_A			= End_A;
		this->Length_A		= Length_A;
		this->Direction_B	= Direction_B;
		this->Start_B		= Start_B;
		this->End_B			= End_B;
		this->Length_B		= Length_B;
	}
	~Overlap()
	{

	}
	inline int getID_A(){
		return ID_A;
	};
	inline int getID_B(){
		return ID_B;
	};
	inline int getDirection_A(){
		return Direction_A;
	};
	inline int getDirection_B(){
		return Direction_B;
	};
	inline int getStart_A(){
		return Start_A;
	};
	inline int getStart_B(){
		return Start_B;
	};
	inline int getEnd_A(){
		return End_A;
	};
	inline int getEnd_B(){
		return End_B;
	};
	inline int getLength_A(){
		return Length_A;
	};
	inline int getLength_B(){
		return Length_B;
	};
	inline float getJaccardScore(){
		return JaccardScore;
	};
	inline int getShared(){
		return Shared;
	};

};

