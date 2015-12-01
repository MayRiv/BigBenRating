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
	function switch_show() {
		  show_bars = !show_bars; // изменяем тип диаграм

		  var new_conf = {
		    series: {
		      stack: show_bars ? true : null,
		      lines: { show: !show_bars },
		      bars: { show: show_bars }
		    }
		  };

		  // обновляем конфиг
		  $.extend(true, plot_conf, new_conf);
		  $.extend(true, overview_conf, new_conf);

		  // перерисовываем
		  redraw();
	}
	function redraw() {
		  var data = [];
		  for(var j = 0; j < all_data.length; ++j)
		    if(!hide[j])
		      data.push(all_data[j]);

		  plot = $.plot($("#placeholder"), data, plot_conf);
		  overview = $.plot($("#overview"), data, overview_conf);

		  // легенду рисуем только один раз
		  plot_conf.legend.show = false;

		  // последний аргумент - чтобы избежать рекурсии
		  overview.setSelection({ x1: selection[0], x2: selection[1] }, true);
	}
  	return {
	trySend: function() {
		if (checkRoles())
			document.getElementById('form').submit()
		else
			alert("Invalid Roles");

	},
	compare: function(player){
		player =  document.getElementById('ComparePlayer').value;

		var xhr = new XMLHttpRequest();

		var body = 'name=' + encodeURIComponent(player);

		xhr.open("POST", '?action=compare', true)
		xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded')

		xhr.onreadystatechange = function() { 
			if (xhr.readyState == 4) { 
		        if(xhr.status == 200) { 
		        	document.getElementById("CompareDiv").innerHTML = xhr.responseText; // Выводим ответ сервера
		        }
		    }
		};

		xhr.send(body);
	},
	tryDelete: function(gameId){
		if (confirm("Вы действительно хотиле удалить игру " + gameId + "?"))
		{
			window.location = "?action=deleteGame&GameId=" + gameId;
		}
	},
	draw: function(){
		var selection = ["2008/12/01", "2010/12/01"];
		// какие данные скрываем - заполняем позже
		var hide = [];
// преобразуем даты в формат, понятный Flot-у
		for(var j = 0; j < all_data.length; ++j) {
 		hide.push(false); // не скрываем j-ый ряд. пока что.
  		for(var i = 0; i < all_data[j].data.length; ++i)
    		all_data[j].data[i][0] = Date.parse(all_data[j].data[i][0]);
		}
		for(var i = 0; i < selection.length; ++i)
  			selection[i] = Date.parse(selection[i]);

		var overview; // "обзор" всех данных внизу страницы
		var plot; // график крупным планом
		var show_bars = false; // показывать столбики или линии
		var plot_conf = {
		  series: {
		    stack: null,
		    lines: { 
		      show: true,
		      lineWidth: 2 
		    }
		  },
		  xaxis: {
		    mode: "time",
		    timeformat: "%y/%m/%d",
		    min: selection[0],
		    max: selection[1]
		  },
		  legend: {
		    container: $("#legend")
		  }
		};

		var overview_conf = {
		  series: {
		    lines: { 
		      show: true,
		      lineWidth: 1
		    },
		    shadowSize: 0
		  },
		  xaxis: {
		    ticks: []
		  },
		  yaxis: {
		    ticks: []
		  },
		  selection: {
		    mode: "x"
		  }, 
		  legend: {
		    show: false
		  }
		};
		 
		// меняем вид - столбики или линии
		

		// перерисовываем все и вся :)
		

		// вычисляем ширину колонки в соответствии с новой областью выделения
		function calc_bar_width() {
		  // поскольку по оси OX откладывается время,
		  // ширина столбцов в гистограмме вычисляется в 1/1000-ых секунды
		  // при масштабировании эту величину следует пересчитать
		  var r = plot_conf.xaxis;
		  // вычисляем, сколько столбцов попало в интервал
		  var bars_count = 0;
		  for(var i = 0; i < all_data[0].data.length; ++i)
		    if(all_data[0].data[i][0] >= r.min &&
		       all_data[0].data[i][0] <= r.max)
		       bars_count++;

		  // изменяем ширину столбцов
		  var new_conf = {
		    series: {
		      bars: { // умножаем на два, чтобы оставалось место между столбцами
		        barWidth: (r.max - r.min)/((bars_count + 1 /* на ноль не делим */) * 2) 
		      }
		    }
		  };
		  $.extend(true, plot_conf, new_conf);
		}

		// вычисляем ширину столбцов в гистограмме
		calc_bar_width();
		// рисуем графики в первый раз
		redraw();

		// событие - новое выделение на overview    
		$("#overview").bind("plotselected", function (event, ranges) {
		  var r = ranges.xaxis;
		  // сохраняем координаты выделенной области
		  selection = [r.from, r.to];

		  // перемещаем обзор в новую область
		  var new_conf = {
		    xaxis: {
		      min: r.from,
		      max: r.to
		    }
		  };
		  $.extend(true, plot_conf, new_conf);
		 
		  calc_bar_width();
		  redraw();
		});

		// рисуем чекбоксы в легенде
		var legend = document.getElementById('legend'); // еще IE не умеет заменять innerHTML в table
		var legend_tbl = legend.getElementsByTagName('table')[0];
		var legend_html = '<table style="font-size: smaller; color: rgb(84, 84, 84);"><tbody>';
		for(var i = 0; i < legend_tbl.rows.length; i++) {
		  legend_html += '<tr>' +
		    '<td><input type="checkbox" onclick="hide['+ i +']=!hide['+ i +'];redraw();" checked="1"></td>'
		    + legend_tbl.rows[i].innerHTML
		    + '</tr>';
		}
		legend_html += "</tbody></table>";
		legend.innerHTML = legend_html;
		}
	}

})();