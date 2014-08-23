<?php
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");

class budget_ligne extends assMetaNode
{
	var $table="organisme_budget_ligne";

	function meta(&$policy)
	{
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	}
	function budget_ligne()
	{
		$this->atkMetaNode();
		$this->atkNode("budget_ligne", NF_ADD_LINK |NF_ADDAFTERADD | NF_COMPACT);
		$organisme = $this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_READONLY| AF_FORCE_LOAD),null,4);
		$this->add(new atkManyToOneRelation("id_budget","organisme.budget",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),null,3);
		$this->add(new atgTextLibelleAttribute("libelle", AF_OBLIGATORY|AF_FORCE_LOAD),null,5);
		$compte = $this->add(new atkManyToOneRelation("id_compte", "organisme.compte", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_FORCE_LOAD),null,6);
		$compte->setDestinationFilter("organisme_compte.id in ( select organisme_compte.id from organisme_compte where ( code like '6%' or code like '7%' or code like '8%') and usuel='1' and id_organisme='[id_organisme.id]') ");

		//	$compte->addDestinationFilter("id_organisme= '[id_organisme.id]' and usuel='1'");
		$this->add(new atkDateAttribute("date_budget", "Y-m-d", "Y-m-d", 0, 0, AF_OBLIGATORY| AF_FORCE_LOAD | AF_DATE_STRING),null,7);
		$this->add(new atkNumberAttribute("debit", AF_SEARCHABLE, 10, 2),null,8);
		$this->add(new atkNumberAttribute("credit",  AF_SEARCHABLE, 10, 2),null,9);
		$this->add(new atkAttribute("id",AF_HIDE_ADD | AF_HIDE_EDIT  | AF_FORCE_LOAD | AF_COMPACT),null,2);
		$this->add(new atkfckattribute("motif", "", AF_HIDE_LIST | AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '100%',
				'Height' => '300px'
		)),null,10);
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,11);
		$this->setSecurityAlias("organisme.organisme");
	}

	function initial_values() {
		$init_vals = array ();
		//	$this->p($this->m_postvars);
		$budget = explode('=', $this->m_postvars['atkfilter']);
		if ($budget[0] == 'organisme_budget_ligne.id_budget') {
			$id_budget = $budget[1];
			$db = & atkGetDb();
			$data = $db->getrows("SELECT b.id_organisme
					FROM organisme_budget b where b.id=$id_budget");
			$init_vals["id_organisme"] = $data[0]["id_organisme"];
		} else {
			echo "L'ajout de ligne de budget n'est possible qu'à partir de la sélection d'un budget.";
			die();
		}
		return $init_vals;
	}

	function descriptor_def()
	{
		return "[libelle]";
	}

	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_display($record, $mode) {
		$res=$this->descripteur_budget_ligne($record["id"],'o');
		$res.=$this->descripteur_organisme_sans_lien($record["id_organisme"]["id"]);
		return $res;
	}
	function validate(&$record, $mode)
	{
		// vérifier date dans année budget
		$id_budget = $record["id_budget"]["id"];
		$an=$record["date_budget"]["year"];
		$db = & atkGetDb();
		$sql = "SELECT an_budget  from organisme_budget
		where id=$id_budget
		and an_budget=$an";
		$data = $db->getrows($sql);
		if (count($data)==0)
		{
			atkTriggerError($record, $this->getAttribute("date_budget"), "La date doit être dans l'année du budget : ".$record["id_budget"]["an_budget"]);
		}
		// Vérifier renseignement débi/crédit
		if (($record["debit"]=="" || $record["debit"]==0) && ($record["credit"]=="" || $record["credit"]==0))
		{
			atkTriggerError($record, $this->getAttribute("debit"), "Crédit ou débit doivent être renseignés");
		}
		if (parent::validate($record, $mode)==true)
		{
			return true;
		}
	}

}

?>