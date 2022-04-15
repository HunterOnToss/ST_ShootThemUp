#pragma once

class STUUtils
{
public:

	template<typename T> 
	static T* GetSTUPlayerController(APawn* PlayerPawn) 
	{
        if (PlayerPawn)
        {
            const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
            return Cast<T>(Component);
        }
        return nullptr;
	}
};