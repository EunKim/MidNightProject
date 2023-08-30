// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpRequestActor.h"
#include "HttpModule.h"
#include "JsonParseLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "instrument.h"
#include "MidNightProjectCharacter.h"
// Sets default values
AHttpRequestActor::AHttpRequestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHttpRequestActor::BeginPlay()
{
	Super::BeginPlay();
	
	/*instrument = Cast<Ainstrument>(UGameplayStatics::GetActorOfClass(this, &Ainstrument::StaticClass()));
	player = Cast<Ainstrument>(UGameplayStatics::GetActorOfClass(this, &AMidNightProjectCharacter::StaticClass()));*/
}

// Called every frame
void AHttpRequestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpRequestActor::PostRequset(const FString url)
{
	TMap<FString, FString> chatData;
	//studentData.Add("Name", "AAA");
	//studentData.Add("Age", "30");
	//studentData.Add("Height", "172");
	
	

	//chatData.Add("id", instrument->id);
	//chatData.Add("text",  player->Chat_UI->text_Answer->GetText());

	//FString chatJsonData = UJsonParseLibrary::MakeJson(chatData);


	//����� �����ϰ�, request �ν��Ͻ��� �����Ѵ�.
	FHttpModule& httpModule = FHttpModule::Get();
	//��û ����
	TSharedRef<IHttpRequest> req = httpModule.CreateRequest();
	req->SetURL(url);
	req->SetVerb(TEXT("POST"));
	req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	//req->SetContentAsString(chatJsonData);
	req->OnProcessRequestComplete().BindUObject(this, &AHttpRequestActor::OnPostData);
	req->ProcessRequest();
}

void AHttpRequestActor::OnPostData(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		FString receivedData = Response->GetContentAsString();

		//FJsonSerializer::Deserialize();
		//���� �����͸� ȭ�鿡 ����Ѵ�.
		//gm->SetLogText(receivedData);

		
	}

	else {

		// ��û ���� ���� Ȯ��
		EHttpRequestStatus::Type status = Request->GetStatus();

		switch (status)
		{
		case EHttpRequestStatus::NotStarted:
			break;
		case EHttpRequestStatus::Processing:
			break;
		case EHttpRequestStatus::Failed:
			break;
		case EHttpRequestStatus::Failed_ConnectionError:
			break;
		case EHttpRequestStatus::Succeeded:
			break;
		default:
			break;
		}


	}
	//���� �ڵ� Ȯ��
	int32 responseCode = Response->GetResponseCode();
	//gm->SetLogText(FString::Printf(TEXT("Response Code : %d"), responseCode));
}
