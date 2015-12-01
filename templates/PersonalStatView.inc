<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Личный кабинет</h1>
	<?php
		//$obj->show();
		echo "<div><h2>Статистика игрока $obj->player</h2>";
		echo "<p>Получил $obj->bestVotes лучших</p>";
		echo "<p>Убит в первую ночь $obj->firstBloodCount раз</p>";
		if($obj->firstBloodCount)
			echo "<p>В среднем $obj->averageBestMove черных в лучших ходе</p></div>";
		

		echo '<body><table class="table_dark">';
		echo "<tr><th>Роль</th><th>Всего сыграно</th><th>Побед</th>";
		echo	"<tr><td>Всего</td><td>$obj->totalGamesCount</td><td>$obj->totalVictoryCount</th></td>";
		echo	"<tr><td>Красный</td><td>$obj->totalRedCountGames</td><td>$obj->totalRedVictoryGames</th></td>";
		echo	"<tr><td>Черный</td><td>$obj->totalBlackCountGames</td><td>$obj->totalBlackVictoryGames</th></td>";
		
		echo "<tr><th colspan='3'>Подробно</th></tr>";
		echo	"<tr><td>Мирный житель</td><td>$obj->citizensGameCount</td><td>$obj->citizensVictoryCount</td></tr>";
		echo	"<tr><td>Шериф</td><td>$obj->sherifGameCount</td><td>$obj->sherifVictoryCount</td></tr>";
		echo	"<tr><td>Мафия</td><td>$obj->mafiaGameCount</td><td>$obj->mafiaVictoryCount</td></tr>";
		echo	"<tr><td>Дон</td><td>$obj->donGameCount</td><td>$obj->donVictoryCount</th></td>";
		
		echo '</table>';

		echo "<div><p>Сыграл в играх: ";
		foreach ($obj->games as $game) {
			echo "<a href='?action=showGame&GameId=".$game."'>".$game."</a> ";
		}
		echo "</p></div>";
		echo '<div  style="margin:auto;"><p><noscript><strong style="color: red;">Для отображения данных необходимо включить JavaScript!</strong></noscript></p>
    <div id="placeholder" style="width:600px;height:300px;display: inline-block;"></div>
    <div style="display: inline-block;">
      <div id="legend"></div>
      <p style="postion:relative;text-align: center;"><a href="#" onclick="switch_show(); return false;">Сменить вид</a></p>
    </div>
    <div style="clear: both;"></div>
    <div id="overview" style="margin-top:20px;width:600px;height:50px;display: inline-block;"></div></div>';
		$games= '<script language="javascript" type="text/javascript">var all_data = [{ label: "Все роли сыграно", color: 0, data: [';
		$start = null;
		foreach ($obj->stat as $date => $stat) {
			if (!isset($start))
				$start = $date;
			$end = $date;
			$games .= "[\"$date\",".(isset($stat['general']['total'])?$stat['general']['total']:0) ."],";
		}
		$games[strlen($games) - 1] = ']';
		$games .= "},";

		$games .= '{ label: "Все роли победы", color: 1, data: [';
		foreach ($obj->stat as $date => $stat) {
			$games .= "[\"$date\",".(isset($stat['general']['victories'])?$stat['general']['victories']:0) ."],";
		}
		$games[strlen($games) - 1] = ']';
		$games .= "}];";

		echo $games;
		echo "var selection = [\"$start\", \"$end\"];";
		//getView("DrawScriptRawPart.inc", null);
	?>
var hide = [];
// преобразуем даты в формат, понятный Flot'у
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

// перерисовываем все и вся :)
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
</script>
<p><a href="?action=changePassword">Сменить пароль</a></p>
</div>

<?php getView("Footer.inc", null); ?>
</body>