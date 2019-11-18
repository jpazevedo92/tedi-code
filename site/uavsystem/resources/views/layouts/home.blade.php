<div class="container-fluid spark-screen">
		<div class="row">
			<div class="col-md-8 col-md-offset-2">

				<!-- Default box -->
				<div class="box">
					<div class="box-header with-border">
						<h3 class="box-title">Applications</h3>

<!-- 						<div class="box-tools pull-right">
							<button type="button" class="btn btn-box-tool" data-widget="collapse" data-toggle="tooltip" title="Collapse">
								<i class="fa fa-minus"></i></button>
							<button type="button" class="btn btn-box-tool" data-widget="remove" data-toggle="tooltip" title="Remove">
								<i class="fa fa-times"></i></button>
						</div> -->

					</div>
					<div class="box-body">
                        <div class="col-md-12">
                            <div class="col-md-3">
                            <button type="button" class="btn btn-primary qgc"><i class="fa fa-assistive-listening-systems"></i> QGroundControl</button>
                            </div>
                            <div class="col-md-9">
                                @foreach(App\Uav::all() as $uav)
                                    @if($uav->name != "Host")
                                        <button type="button" class="btn btn-info start_vm" id="{{$uav->id}}"><i class="fa fa fa-location-arrow"></i> {{$uav->name}}</button>
                                    @endif
                                @endforeach
                            </div>
                        </div>

					</div>
					<!-- /.box-body -->
				</div>
				<!-- /.box -->
                				<!-- Default box -->
				<div class="box">
					<div class="box-header with-border">
						<h3 class="box-title">Configurations</h3>

<!-- 						<div class="box-tools pull-right">
							<button type="button" class="btn btn-box-tool" data-widget="collapse" data-toggle="tooltip" title="Collapse">
								<i class="fa fa-minus"></i></button>
							<button type="button" class="btn btn-box-tool" data-widget="remove" data-toggle="tooltip" title="Remove">
								<i class="fa fa-times"></i></button>
						</div> -->
					</div>
					<div class="box-body">
						{{ trans('adminlte_lang::message.logged') }}. Start creating your amazing application!
					</div>
					<!-- /.box-body -->
				</div>
				<!-- /.box -->

			</div>
		</div>
	</div>