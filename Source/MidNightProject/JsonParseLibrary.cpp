// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonParseLibrary.h"
#include "Serialization/JsonSerializer.h"

FString UJsonParseLibrary::JsonParse(const FString& originData)
{
	FString parsedData;

	//josn������ �Ľ� ���
	//1.Reader or  Writer(������) �� �����.
	TSharedRef<TJsonReader<TCHAR>> reader = TJsonReaderFactory<TCHAR>::Create(originData);

	//2.Reader �� �Ľ�(�����м�)�� ����� json Object �� �����Ѵ�.
	TSharedPtr<FJsonObject> result = MakeShareable(new FJsonObject());

	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, FString::Printf(TEXT("JsonParse")));

	//3. �ص��ϱ� (Deserialize: ������ȭ , Serialize : ����ȭ)
	if (FJsonSerializer::Deserialize(reader, result))
	{
		 //result->GetObjectField("content");
		//result->GetObjectFiled("content");
		//result->TryGetObjectField("contnet",);

		//json value�� items��� value���� ã�ƿ� value �� ����ȭ ���� ���� �ֻ�� �θ�ü : FJsonValue
		TArray<TSharedPtr<FJsonValue>> parsedDataArray = result->GetArrayField("items");

		//parsedDataArray->As

		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, FString::Printf(TEXT("Deserialize")));

		//item �迭 ���� �ϳ��ϳ���  ã���鼭 � ��ü�� ã������ ���ϱ�
		for (TSharedPtr<FJsonValue> pd : parsedDataArray)
		{
			parsedData = pd->AsObject()->GetStringField("content");
			//FString authorName = pd->AsObject()->GetStringField("aut_nm");
			//parsedData.Append(FString::Printf(TEXT("BookName : %s\n AuthorName : %s\n\n"), *bookdName, *authorName));
			//GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Yellow, text_answer);
		}

	}

	return parsedData;
}

FString UJsonParseLibrary::MakeJson(const TMap<FString, FString> source)
{
	// josn Object�� �����ϰ� ���� �ִ´�. {} �� �ִ� ����
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

	for (TPair<FString, FString> kv : source)
	{
		// Ű�� value �� �ֱ�
		jsonObj->SetStringField(kv.Key, kv.Value);

	}

	// Writer�� �����ϰ�, json object ���ڵ��Ѵ�.
	FString jsonData;

	TSharedRef<TJsonWriter<TCHAR>> writer = TJsonWriterFactory<TCHAR>::Create(&jsonData);
	FJsonSerializer::Serialize(jsonObj.ToSharedRef(), writer);

	return jsonData;
}


