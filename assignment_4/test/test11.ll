; ModuleID = 'test11.ll'
source_filename = "test11.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #0 {
  %1 = alloca [10 x i32], align 16
  call void @llvm.memset.p0.i64(ptr align 16 %1, i8 0, i64 40, i1 false)
  br label %2

2:                                                ; preds = %7, %0
  %.01 = phi i32 [ 4, %0 ], [ %8, %7 ]
  %3 = icmp slt i32 %.01, 8
  br i1 %3, label %4, label %9

4:                                                ; preds = %2
  %5 = sext i32 %.01 to i64
  %6 = getelementptr inbounds [10 x i32], ptr %1, i64 0, i64 %5
  store i32 %.01, ptr %6, align 4
  br label %7

7:                                                ; preds = %4
  %8 = add nsw i32 %.01, 1
  br label %2, !llvm.loop !6

9:                                                ; preds = %2
  br label %10

10:                                               ; preds = %16, %9
  %.0 = phi i32 [ 4, %9 ], [ %17, %16 ]
  %11 = icmp slt i32 %.0, 8
  br i1 %11, label %12, label %18

12:                                               ; preds = %10
  %13 = add nsw i32 %.0, 1
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds [10 x i32], ptr %1, i64 0, i64 %14
  store i32 %.0, ptr %15, align 4
  br label %16

16:                                               ; preds = %12
  %17 = add nsw i32 %.0, 1
  br label %10, !llvm.loop !8

18:                                               ; preds = %10
  %19 = getelementptr inbounds [10 x i32], ptr %1, i64 0, i64 0
  %20 = load i32, ptr %19, align 16
  %21 = getelementptr inbounds [10 x i32], ptr %1, i64 0, i64 5
  %22 = load i32, ptr %21, align 4
  %23 = add nsw i32 %20, %22
  ret i32 %23
}

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #1

attributes #0 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nounwind willreturn memory(argmem: write) }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Debian clang version 19.1.4 (1~deb12u1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
