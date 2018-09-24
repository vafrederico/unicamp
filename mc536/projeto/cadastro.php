<?php 
	if(!isset($_SESSION)){
		session_start();
	}
	if(isset($_SESSION['usuario']) && $_SESSION['usuario'] != -1)
		header('Location: index.php');

	require("phar://neo4jphp.phar");
	use Everyman\Neo4j\Client,
        Everyman\Neo4j\Index\NodeIndex,
		Everyman\Neo4j\Index\RelationshipIndex,
        Everyman\Neo4j\Relationship,
        Everyman\Neo4j\Node,
        Everyman\Neo4j\Cypher;
	if(isset($_POST['nome'])){
		$client = new Client();
		$run = "MERGE (p:Person {usuario: '{$_POST['usuario']}'}) " .
				"ON CREATE p " .
					"SET p.nome = '{$_POST['nome']}', p.natal = '{$_POST['natal']}', p.password='" . md5($_POST['senha']) . "' " .
				"ON MATCH p " . 
					"set p.existed=true " . 
				"return p.existed, p.usuario";
		$query = new Cypher\Query($client, $run);
        $result = $query->getResultSet();
        foreach($result as $row) {
        	$existed = ($row->offsetGet('p.existed')?true:0);
        	$usuario = $row->offsetGet('p.usuario');
	    }
	    if(!$existed){
	    	$_SESSION['usuario'] = $usuario;
	    	header('Location: login.php');
	    } else {
	    	echo "Pessoa já cadastrada!<br>";
	    }
	}
?>
<form method="POST">
	Nome: <input type='text' name='nome'><br>
	Usuário: <input type='text' name='usuario'><br>
	Senha: <input type='password' name='senha'><br>
	Cidade Natal: <input type='text' name='natal'><br>
	<input type='submit'>
</form>