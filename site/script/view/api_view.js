Application.ApiView = Ember.View.extend({
	menu: Application.ApiMenu,
	content: Application.ApiContent,
	_updateContentViewTemplate: function(templateName) {
		var view = this;

		var contentView = view.get('contentViewInstance');
		contentView.updateTemplate(templateName);
	}	
});