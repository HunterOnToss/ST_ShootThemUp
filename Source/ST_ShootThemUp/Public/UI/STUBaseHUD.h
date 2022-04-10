// Shoot Them Up Game. All Right Reserved 2022.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUBaseHUD.generated.h"

UCLASS()
class ST_SHOOTTHEMUP_API ASTUBaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:

    virtual void DrawHUD() override;

private:

	void DrawCrosshair();
};
