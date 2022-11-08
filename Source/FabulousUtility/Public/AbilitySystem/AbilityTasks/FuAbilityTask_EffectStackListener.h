#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "FuAbilityTask_EffectStackListener.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FFuEffectStackListenerDelegate, FActiveGameplayEffectHandle, EffectHandle,
                                               int32, NewCount, int32, PreviousCount);

UCLASS(DisplayName = "Fu Effect Stack Listener Ability Task")
class FABULOUSUTILITY_API UFuAbilityTask_EffectStackListener : public UAbilityTask
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName = "Effect Class")
	TSubclassOf<UGameplayEffect> EffectClass1;

public:
	UPROPERTY(BlueprintAssignable, Category = "Fabulous Utility|Fu Effect Stack Listener Ability Task")
	FFuEffectStackListenerDelegate OnStackChanged;

public:
	UFUNCTION(BlueprintCallable, Category = "Fabulous Utility|Fu Ability Tasks", BlueprintInternalUseOnly,
		Meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UFuAbilityTask_EffectStackListener* FuWaitForEffectStackChange(UGameplayAbility* OwningAbility,
	                                                                      TSubclassOf<UGameplayEffect> EffectClass);

protected:
	virtual void Activate() override;

	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	void OnActiveGameplayEffectAdded(UAbilitySystemComponent* AbilitySystem,
	                                 const FGameplayEffectSpec& EffectSpecification,
	                                 FActiveGameplayEffectHandle EffectHandle) const;

	void OnActiveGameplayEffectRemoved(const FActiveGameplayEffect& ActiveEffect) const;

	void OnEffectStackChanged(FActiveGameplayEffectHandle EffectHandle, int32 NewCount, int32 PreviousCount) const;
};
