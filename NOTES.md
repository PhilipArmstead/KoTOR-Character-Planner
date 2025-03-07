Notes
===

# Character attributes

[Character class](https://bitbucket.org/PhilArmstead/dnd/src/lerna/packages/rules/src/classes/Character/Character.js)

```ts
getCostOfAttributePoints (level: number, attributes) {
	let cost = 0
	if (level === 1) {
		attributes.forEach((value) => {
			for (let stat = CONSTANTS.CHARACTER_CREATION_MINIMUM_ATTRIBUTE + 1; stat <= value; ++stat) {
				cost += this.getAttributePointCost(level, stat)
			}
		})
	} else {
		cost = Object.entries(attributes).reduce((accumulator, [, value]) => accumulator + value, 0)
	}

	return cost
}
```

[Attribute component](https://bitbucket.org/PhilArmstead/dnd-frontend/src/30ee8ffd18c07f95eaf22c017ceb6943086410a4/src/components/character/level-up/CharacterLevelUpAttributes.vue)

```ts
const pointsRemaining = computed(() => levelUpAttributeAllowance.value - pointsSpent.value)

const getPointCost = (attributeIndex, value) => {
	// Are we counting upwards or downwards?
	if (value < modifiedAttributes.value[attributeIndex].value) {
		return Character.getAttributePointCost(props.character.level, value + 1) * -1
	} else {
		return Character.getAttributePointCost(props.character.level, value)
	}
}

const updateAttribute = (event, index) => {
	const value = Number(event.target.value)

	if (value <= 18 && value >= props.character.attributes[index].base) {
		const pointCost = getPointCost(index, value)

		if (pointCost <= pointsRemaining.value) {
			modifiedAttributes.value[index].value = value
			pointsSpent.value += pointCost
		}
	}

	event.target.value = modifiedAttributes.value[index].value
}
```