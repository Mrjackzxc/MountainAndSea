// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
template<class T>
class MOUNTAINANDSEA_API TsingletonBase
{
protected:
	TsingletonBase();
	~TsingletonBase();

protected:
	static T s_tInstance;

public:
	static T * GetInstance() { return s_tInstance; }

};

template<class T>
T TsingletonBase<T>::s_tInstance;



