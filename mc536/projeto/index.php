<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1){
		echo "Bem-vindo " . $_SESSION['usuario'] . "<br>";
		if($_SESSION['usuario'] == 'admin')
			echo "<a href='listagem.php'>Editar pessoas</a><br>";

		echo "<a href='conhecidos.php'>Conhecidos</a><br>";
		echo "<a href='artistas.php'>Artistas</a><br>";
		echo "<a href='editPerson.php'>Editar perfil</a><br>";
		echo "<a href='logout.php'>Logout</a><br>";
	} else {
		echo "<a href='login.php'>Login</a><br>";
		echo "<a href='cadastro.php'>Cadastro</a><br>";
	}
	echo "<a href='stats.php'>Estatísticas</a>";
	
?>