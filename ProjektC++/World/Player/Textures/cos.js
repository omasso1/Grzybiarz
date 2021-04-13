    const getRandomTileWeather = (firstInit = false) => {
        if (firstInit) {
            sendChat(apiName,'<strong>Inicjalizacja początkowej pogody zakończona.</strong> \nPogoda dla poszczególnych rejonów to:');
            weatherArray = [];
            initWeatherArray();
        }
        if (!firstInit) {
             sendChat(apiName,'<strong>Zmiana pogody dla nowej rundy!</strong> \nPogoda zmieniła się dla rejonów:');
        }
		let tableText = "<table>";
        for(let tileIndex = 0; tileIndex < weatherArrayTilesAmount; tileIndex++){
			tableText+="<tr><td>";
            let randomNumber = Math.floor(Math.random() * weatherNames.length);
            while (weatherArray[tileIndex][randomNumber] === 0) {
                randomNumber = Math.floor(Math.random() * weatherNames.length);  
            } 
            if (weatherArray[tileIndex][randomNumber] === sameWeatherMaxDuration){
                let generatedTable = [];
                for (let tableIndex = 0; tableIndex < weatherNames.length; tableIndex++){
                    generatedTable[tableIndex] = sameWeatherMaxDuration;
                }
                weatherArray[tileIndex] = generatedTable;    
            }
            weatherArray[tileIndex][randomNumber] = weatherArray[tileIndex][randomNumber] - 1;
            if (firstInit) {
                tableText += tileIndex +': '+String(weatherNames[randomNumber]);
            } 
            if (!firstInit && weatherArray[tileIndex][randomNumber] === sameWeatherMaxDuration - 1) {
                tableText += tileIndex +': '+String(weatherNames[randomNumber]);
            }
			tableText+="</tr></td>";
        }
		tableText+="</table>";
		sendChat(apiName,tableText);
    }