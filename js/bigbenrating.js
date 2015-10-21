var bbr = (function() {

	var version;
	function checkRoles()
	{
		var arr = [];
		countMaf = 0;
		countSherif = 0;
		countDon = 0;
		countCit = 0;
		for (i=0; i < 10; i++){
			var role = document.getElementById('Role'+i).value
			if(role=="Don")
				countDon++;
			if(role=="Citizen")
				countCit++;
			if(role=="Mafia")
				countMaf++;
			if(role=="Sherif")
				countSherif++;
			
		}
		if (countSherif == 1 && countDon == 1 && countCit == 6 && countMaf == 2)
		return true;
		else return false;
	}

  return {
    trySend: function() {
		if (checkRoles())
			document.getElementById('form').submit()
		else
			alert("Invalid Roles");

	}
  }

})();