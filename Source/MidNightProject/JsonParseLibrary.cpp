// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLibrary.h"

FString UJsonParseLibrary::JsonParse(const FString& originData)
{
	FString parsedData;

	//josn������ �Ľ� ���
	//1.Reader or  Writer(������) �� �����.
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	//2.Reader �� �Ľ�(�����м�)�� ����� json Object �� �����Ѵ�.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	//3. �ص��ϱ� (Deserialize: ������ȭ , Serialize : ����ȭ)
	if (FJsonSerializer::Deserialize(reader, result))
	{
		//json value�� items��� value���� ã�ƿ� value �� ����ȭ ���� ���� �ֻ�� �θ�ü : FJsonValue
		TArray<TSharedPtr<FJsonValue>> parsedDataArray = result->GetArrayField("items");

		//item �迭 ���� �ϳ��ϳ���  ã���鼭 � ��ü�� ã������ ���ϱ�
		for (TSharedPtr<FJsonValue> pd : parsedDataArray)
		{
			FString bookdName = pd->AsObject()->GetStringField("bk_nm");
			FString authorName = pd->AsObject()->GetStringField("aut_nm");
			parsedData.Append(FString::Printf(TEXT("BookName : %s\n AuthorName : %s\n\n"), *bookdName, *authorName));
		}
	}

	return parsedData;
}

//FString UJsonParseLibrary::MakeJson(const TMap<FString, FString> source)
//{
//	
//}
