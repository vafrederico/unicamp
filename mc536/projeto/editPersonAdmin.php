<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
		$client = new Client();

	if(!(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1 && $_SESSION['usuario'] = 'admin'))
		header('Location: login.php');

		error_reporting(E_ALL);
		
	
	if(isset($_POST['nome'])){
		$run = "" . 
"MATCH (n:Person) " .
"WHERE n.usuario='{$_POST['usuarioold']}' " .
"SET n.nome = '{$_POST['nome']}', " .
"n.natal = '{$_POST['natal']}', " . 
"n.usuario = '{$_POST['usuario']}' ";
	if(isset($_POST['senha']) && $_POST['senha'] != "")
		$run .= ", n.password = '" . md5($_POST['senha']) . "' ";
	$run .= "return n";

		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        header('Location: listagem.php');

	}
			$run = "" . 
"MATCH (n:Person) " .
"WHERE n.usuario='{$_GET['usuario']}' " .
"return n.nome, n.natal, n.usuario";
$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        $row = $result->offsetGet(0);
?>
<form method="POST">
	Nome: <input type='text' name='nome' value='<?php echo $row->offsetGet('n.nome'); ?>'><br>
	<input type='hidden' name='usuarioold' value='<?php echo $row->offsetGet('n.usuario'); ?>'>
	Usuário: <input type='text' name='usuario' value='<?php echo $row->offsetGet('n.usuario'); ?>'><br>
	Senha: <input type='password' name='senha' value=''><br>
	Cidade Natal: <input type='text' name='natal' value='<?php echo $row->offsetGet('n.natal'); ?>'><br>
	<input type='submit'>
</form>