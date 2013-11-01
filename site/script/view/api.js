Application.ApiView = Ember.View.extend({
	didInsertElement: function() {
		var view = this;
		view._setupMenu();
	},
	_setupMenu: function() {
		$('#index a').next('div').siblings('div').slideUp();
            $('#index a').click(function(e) {            
            	$(e.target).next('div').siblings('div').slideUp();
            	$(e.target).siblings('a').css('color', '#6d6e70');            
            	$(e.target).next('div').slideToggle();
            	$(e.target).css('color', '#00979C');
        });
	}
});